## Philosophy

When you build an agent with LangGraph, you will first break it apart into **discrete steps** called **nodes**. Then, you will describe the different decisions and transitions from each of your nodes. Finally, you connect nodes together through a **shared state** that each node can read from and write to.

## Node

A node in LangGraph is just a Python function that takes the current state and returns updates to it. Nodes take state, do work, and return updates.

## WalkThrough

https://docs.langchain.com/oss/python/langgraph/thinking-in-langgraph

### What belongs in state?

**Include in state if**
    * Does it need to persist across steps? If yes, it goes in state.

**Don't store**
    * Can you derive it from other data? If yes, compute it when needed instead of storing it in state.

**A key principle: your state should store raw data, not formatted text. Format prompts inside nodes when you need them.**

Benefits:

* Different nodes can format the same data differently for their needs
* You can change prompt templates without modifying your state schema
* Debugging is clearer—you see exactly what data each node received
* Your agent can evolve without breaking existing state

## Conditional Edges


# LangGraph：Interrupt API 与使用方式

## 1. Interrupt 是什么？

`interrupt()` 用于：

> 在节点执行过程中暂停 Graph，把数据发送给外部，等待人工或外部系统返回结果，然后继续执行。

典型场景：

* 人工审批
* 人工修改模型生成内容
* 高风险工具调用确认
* 等待用户补充信息
* 前端执行本地操作后返回结果

---

## 2. API 形式

概念上可以理解为：

```python
def interrupt(value: JSONSerializable) -> Any:
    ...
```

使用方式：

```python
result = interrupt(payload)
```

其中：

```text
payload
暂停时发送给外部的数据

result
恢复执行时，外部传回的数据
```

`payload` 可以是任意 JSON 可序列化值：

```python
interrupt("是否批准？")

interrupt({
    "question": "是否发送邮件？",
    "draft": "邮件草稿",
})

interrupt([
    {"id": 1, "content": "第一项"},
    {"id": 2, "content": "第二项"},
])
```

字典中的 key 都是业务自定义字段，不是 LangGraph 的标准字段。例如：

```python
{
    "approved": False,
    "edited_response": "Draft response",
}
```

其中的 `approved` 和 `edited_response` 都是开发者自己定义的。

---

## 3. 基本使用示例

```python
from typing import TypedDict

from langgraph.checkpoint.memory import InMemorySaver
from langgraph.graph import StateGraph, START, END
from langgraph.types import Command, interrupt


class EmailState(TypedDict):
    response_text: str | None


def human_review(state: EmailState) -> dict:
    review_result = interrupt(
        {
            "approved": False,
            "edited_response": state.get("response_text") or "",
        }
    )

    if review_result["approved"]:
        return {
            "response_text": review_result["edited_response"]
        }

    return {
        "response_text": None
    }


app = (
    StateGraph(EmailState)
    .add_node("human_review", human_review)
    .add_edge(START, "human_review")
    .add_edge("human_review", END)
    .compile(checkpointer=InMemorySaver())
)
```

---

## 4. 第一次执行：Graph 暂停

```python
config = {
    "configurable": {
        "thread_id": "email-review-001",
    }
}

result = app.invoke(
    {
        "response_text": "Initial draft",
    },
    config=config,
)
```

执行到：

```python
review_result = interrupt({...})
```

时，Graph 会暂停。

此时：

```python
review_result
```

还没有值，节点后面的代码暂时不会继续执行。

使用普通 `invoke()` 时，interrupt 信息可以从：

```python
result["__interrupt__"]
```

中读取。使用 `stream_events(..., version="v3")` 时，可以通过：

```python
stream.interrupted
stream.interrupts
```

读取暂停状态和 payload。

---

## 5. 恢复执行

人工审核后，通过：

```python
Command(resume=...)
```

恢复：

```python
human_input = {
    "approved": True,
    "edited_response": "人工修改后的回复",
}

final_state = app.invoke(
    Command(resume=human_input),
    config=config,
)
```

必须继续使用相同的：

```python
thread_id = "email-review-001"
```

恢复后：

```python
review_result
```

的值就是：

```python
{
    "approved": True,
    "edited_response": "人工修改后的回复",
}
```

因此节点最终返回：

```python
{
    "response_text": "人工修改后的回复"
}
```

并更新 Graph State。传给 `Command(resume=...)` 的值，会成为暂停节点中 `interrupt()` 的返回值。

---

## 6. 完整流程

```text
节点开始执行
    ↓
interrupt(payload)
    ↓
Graph 保存 checkpoint 并暂停
    ↓
外部读取 payload
    ↓
人工或客户端完成操作
    ↓
Command(resume=result)
    ↓
使用相同 thread_id 恢复
    ↓
result 成为 interrupt() 的返回值
    ↓
节点继续处理并返回 State update
```

---

## 7. Checkpointer 和 thread_id

Interrupt 要求 Graph 能保存暂停位置，因此通常需要：

```python
.compile(
    checkpointer=InMemorySaver()
)
```

调用时还需要：

```python
config = {
    "configurable": {
        "thread_id": "唯一任务 ID"
    }
}
```

作用分别是：

```text
checkpointer
保存 State 和暂停位置

thread_id
定位应该恢复哪一条执行
```

恢复时如果换了新的 `thread_id`，LangGraph 找不到原来的暂停状态，会被视为一条新 thread。

---

## 8. 常见错误

### 错误一：不接收返回值

```python
def human_review(state):
    interrupt({
        "draft": state["response_text"]
    })

    return {
        "response_text": "placeholder"
    }
```

人工返回的数据会被忽略，最终固定更新成：

```python
{
    "response_text": "placeholder"
}
```

正确写法：

```python
def human_review(state):
    result = interrupt({
        "draft": state["response_text"]
    })

    return {
        "response_text": result["edited_response"]
    }
```

### 错误二：恢复时使用新 thread_id

```python
# 暂停
thread_id = "thread-1"

# 错误：恢复时换成 thread-2
thread_id = "thread-2"
```

必须使用同一个 `thread_id`。

### 错误三：在 interrupt 前执行不可重复的副作用

恢复时，包含 `interrupt()` 的节点会从节点开头重新执行，因此 `interrupt()` 前面的代码可能再次运行。不要在它前面直接扣款、发送邮件或写入不可重复数据；必要时应把副作用放到审批通过之后，或者实现幂等性。

---

## 9. 最简记忆

```python
answer = interrupt(question)
```

第一次执行：

```text
把 question 发出去并暂停
```

恢复：

```python
Command(resume=answer_value)
```

恢复后：

```python
answer == answer_value
```

而节点中的：

```python
return {"field": value}
```

才是真正提交给 LangGraph 的 State update。


## Resilience Tradeoff


You might wonder: why not combine Read Email and Classify Intent into one node?
Or why separate Doc Search from Draft Reply?
The answer involves trade-offs between resilience and observability.
The resilience consideration: LangGraph’s persistence layer creates checkpoints at node boundaries. When a workflow resumes after an interruption or failure, it starts from the beginning of the node where execution stopped. Smaller nodes mean more frequent checkpoints, which means less work to repeat if something goes wrong. If you combine multiple operations into one large node, a failure near the end means re-executing everything from the start of that node.


## Persistence


Persistence lets LangGraph applications keep useful information beyond a single graph run. It matters when an agent needs to continue a conversation, resume after an interruption, recover from a failure, or remember information across interactions.
LangGraph provides two complementary persistence systems:
Checkpointers persist a thread’s graph state as checkpoints. Use them for short-term, thread-scoped memory, including conversation continuity, human-in-the-loop workflows, time travel, and fault tolerance.
Stores persist application-defined data outside the graph state. Use them for long-term, cross-thread memory, including user preferences, facts, and shared knowledge.
