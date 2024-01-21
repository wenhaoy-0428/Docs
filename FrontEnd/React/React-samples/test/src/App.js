import React, {useState, useEffect} from 'react'

function App() {

  const [counter, setCount] = useState(0);
  useEffect(() => {
    console.log("EFFECT CALLED");
    return function cleanup() {
      console.log("EFFECT DESTROYED");
    }
  })

  return (
    <div className="App" onClick={() => setCount(counter + 1)}>
      {counter}
    </div>
  );
}

export default App;
