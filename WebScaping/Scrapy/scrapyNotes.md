## Installation

Follow the instructions of configuring python virtual env as well as python version management described in [][Python Notes](../../BackEnd/Python/pythonNotes.md#python-env)


## Overall Guide Reference

[freeCodeCamp Scrapy Beginners Course](https://thepythonscrapyplaybook.com/freecodecamp-beginner-course/freecodecamp-scrapy-beginners-course-part-3-scrapy-project/#how-to-create-a-scrapy-project)

[Youtube Version of Above](https://www.youtube.com/watch?v=mBoX_JCKZTE)


## [Structure](https://thepythonscrapyplaybook.com/freecodecamp-beginner-course/freecodecamp-scrapy-beginners-course-part-3-scrapy-project/)

This structure illustrates the **5** main building blocks of every Scrapy project: **Spiders, Items, Middlewares, Pipelines and Settings.**

* `settings.py` is where all your project settings are contained, like activating pipelines, middlewares etc. Here you can change the delays, concurrency, and lots more things.
* `items.py` is a model for the extracted data. You can define a custom model (like a ProductItem) that will inherit the Scrapy Item class and contain your scraped data.
* `pipelines.py` is where the item yielded by the spider gets passed, it’s mostly used to clean the text and connect to file outputs or databases (CSV, JSON SQL, etc).
* `middlewares.py` is useful when you want to modify how the request is made and scrapy handles the response.
* `scrapy.cfg` is a configuration file to change some deployment settings, etc.

## Settings

To include [pipelines](#pipelinesfreecodecamp-scrapy-beginners-course-part-6-items--item-pipelines), [items](#items) and [middlewares](#middleware), we have to specify the class names associated with them in the `settings.py`

```py
DOWNLOADER_MIDDLEWARES = {
    'bookscraper.middlewares.ScrapeOpsFakeUserAgentMiddleware': 400,
}
```

> The number behind the indicates the precedence, which is self-defined. The lower the number is, the higher the precedence is. So that the order of pipelines and middlewares can be easily determined.

## Spider

The spider class mainly used to parse the response and extract the information we're interested in.

After implementing the `parse` function, we can start to scraping by running:

```bash
scrapy crawl your-spider
```

> add `-O filename` option if you wish to store the output to a file.

Since scraping is all about switching between implementing and inspecting the elements, it's much easier to use the interactive shell to try the codes first.

```
scrapy shell
```

During parsing, we can encounter may `yield`s. This is the lazy computation feature of python, which can be leant more in the [yield keyword of python
]()



## XPath

XPath (XML Path Language) is a query language used to navigate and select elements from an XML document. It provides a way to traverse the structure of XML data and extract specific information based on element names, attributes, or other patterns.

Normally, we use CSS selector to select element in the response based on their class names and attributes. However CSS selector doesn't give us a way to navigate in the DOM tree. When encounter cases where the target has to class names and attributes, e.g a solo `<p>` tag, we can hardly select it using CSS selector. However, using XPATH, we can select its neighbor with attributes then using `preceding_siblings` or `following_siblings` to get the target element.


```python
book.xpath("//div[@id='product_description']/following-sibling::p/text()").get()
```


## [Extract Tables](https://youtu.be/mBoX_JCKZTE?t=3985)


## Getting into detail page


To get into detail page, we normally declare a different parse function which will be used as a callback function to the detail page request.

```py
import scrapy

class BookspiderSpider(scrapy.Spider):
    name = 'bookspider'
    allowed_domains = ['books.toscrape.com']
    start_urls = ['https://books.toscrape.com/']

    def parse(self, response):
        books = response.css('article.product_pod')
        for book in books:
            relative_url = book.css('h3 a').attrib['href']
            if 'catalogue/' in relative_url:
                book_url = 'https://books.toscrape.com/' + relative_url
            else:
                book_url = 'https://books.toscrape.com/catalogue/' + relative_url
            yield scrapy.Request(book_url, callback=self.parse_book_page)

        ## Next Page        
        next_page = response.css('li.next a ::attr(href)').get()
        if next_page is not None:
            if 'catalogue/' in next_page:
                next_page_url = 'https://books.toscrape.com/' + next_page
            else:
                next_page_url = 'https://books.toscrape.com/catalogue/' + next_page
            yield response.follow(next_page_url, callback=self.parse)

    def parse_book_page(self, response):
        book = response.css("div.product_main")[0]
        table_rows = response.css("table tr")
        yield {
            'url': response.url,
            'title': book.css("h1 ::text").get(),
            'upc': table_rows[0].css("td ::text").get(),
            'product_type': table_rows[1].css("td ::text").get(),
            'price_excl_tax': table_rows[2].css("td ::text").get(),
            'price_incl_tax': table_rows[3].css("td ::text").get(),
            'tax': table_rows[4].css("td ::text").get(),
            'availability': table_rows[5].css("td ::text").get(),
            'num_reviews': table_rows[6].css("td ::text").get(),
            'stars': book.css("p.star-rating").attrib['class'],
            'category': book.xpath("//ul[@class='breadcrumb']/li[@class='active']/preceding-sibling::li[1]/a/text()").get(),
            'description': book.xpath("//div[@id='product_description']/following-sibling::p/text()").get(),
            'price': book.css('p.price_color ::text').get(),
        }
```


## Items

Normally, after scraping, we're going to return a map object that stores the information we're interested in. This can be done in the parser by returning an object. However, this is not clean enough, it would be better if we define a class somewhere as a template and initialize that class with the data we extracted.

## Item Loader

For a cleaner data collection, we can use ItemLoader that has preprocessor functions we can define so that all data inserted will be preprocessed automatically.

```py
    l = ItemLoader(item=NutritionItem(), selector=response)
    # Use TakeFirst to store a single value instead of a list
    l.default_output_processor = TakeFirst()
    # name
    l.add_css("name", ".nutritionFactsTitle::text")

    # calorie
    calorie = {
        'value': response.css(".nft-cal-amt::text").get(),
        'dv': '-'
    }
    if calorie['value'] == '--':
        return
    l.add_value("calorie", calorie, MapCompose(self.clean_data))

    ...
    yield l.load_item()
```

Item loader supports `add_css` that uses css selector `add_xpath` and `add_value` which is random value we can use.


## [Pipelines](freeCodeCamp Scrapy Beginners Course Part 6: Items & Item Pipelines)

Pipelines are all about **post processing**, which includes data cleaning, data storage and so on.

To do it, we'll have to include the pipeline name inside the `settings.py`:

```py
## settings.py

ITEM_PIPELINES = {
   'bookscraper.pipelines.BookscraperPipeline': 300,
}
```

The main structure of a pipeline looks like this:


```py
from itemadapter import ItemAdapter

class BookscraperPipeline:

    def process_item(self, item, spider):
        adapter = ItemAdapter(item)

        ## Strip all whitespaces from strings
        field_names = adapter.field_names()
        for field_name in field_names:
            if field_name != 'description':
                value = adapter.get(field_name)
                adapter[field_name] = value.strip()
```

> We use an adapter which gives us a uniform field accessor. 

> The configure each field as needed.

Since, it takes some effort to make pipeline works, even though not much, in cases where we have only 1 or 2 fields that need to be cleaned. We can use [serializer](https://youtu.be/mBoX_JCKZTE?t=5135) of [items](#items) instead.


```py
def serializer_price(value):
    return f'$ str(value)'

class BookItem(scrapy.Item):
    price = scrapy.Field(serializer = serializer_price)
    ...
```


## Bypassing

In reality, many sites prevent bots to scape data from them, the technique used to identify bots normally relies on the header of the requests. Since bots can do requests quickly in a short amount of time with the identity information embedded in the header, it can be easily detected. Therefore, to bypass we'll be changing the header of request frequently. 

Some key aspects of the header that will be focusing on are `IP address`, `User Agent`.

### Fake User Agent

One simple way of switching User Agent for requesting is to declare a list of user agent then random select one for each request, as the followings.

```py
## myspider.py

import random

user_agent_list = [
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36',
    'Mozilla/5.0 (iPhone; CPU iPhone OS 14_4_2 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.0.3 Mobile/15E148 Safari/604.1',
    'Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1)',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.141 Safari/537.36 Edg/87.0.664.75',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36 Edge/18.18363',
]

def start_requests(self):
    for url in self.start_urls:
        return Request(url=url, callback=self.parse,
                       headers={"User-Agent": user_agent_list[random.randint(0, len(user_agent_list)-1)]})
```

However, this is normally not sufficient for a large website, and increasing the size of the list is also a dirty work by hand.


Hence, we'll be using Middleware that helps us to forward the request and add some "ingredient" along the way.

[scrapeOps](https://scrapeops.io/docs/fake-user-agent-headers-api/fake-user-agents/) provides free api to generate random User Agents.


## Proxy

* [Proxy List](https://thepythonscrapyplaybook.com/freecodecamp-beginner-course/freecodecamp-scrapy-beginners-course-part-9-rotating-proxies/#how-to-integrate--rotate-proxy-lists)

* [Proxy API](https://thepythonscrapyplaybook.com/freecodecamp-beginner-course/freecodecamp-scrapy-beginners-course-part-9-rotating-proxies/#how-to-use-proxy-apis)


For Proxy API, which is normally a paid service, all we need to do is carry our target URL and call the API. The service will do its own work to handle the request and guarantee the result.


```py
def get_proxy_url(url):
    payload = {'api_key': API_KEY, 'url': url}
    proxy_url = 'https://proxy.scrapeops.io/v1/?' + urlencode(payload)
    return proxy_url

class BookspiderSpider(scrapy.Spider):
    name = 'bookspider'
    allowed_domains = ['books.toscrape.com', 'PROXY_DOMAIN']
    start_urls = ['https://books.toscrape.com/']

    def parse(self, response):
        books = response.css('article.product_pod')
        for book in books:
            relative_url = book.css('h3 a').attrib['href']
            if 'catalogue/' in relative_url:
                book_url = 'https://books.toscrape.com/' + relative_url
            else:
                book_url = 'https://books.toscrape.com/catalogue/' + relative_url
            yield scrapy.Request(get_proxy_url(book_url), callback=self.parse_book_page)
```

> So for every request, our side, the URL will be the url to the Proxy Service, which carries the target url as well. However, in the above code snippet, you can notice that the very first request to the `books.toscrape.com/` (which is automatically done by scrapy) is not done by proxy. To handle this, we can implement a function called `start_request`

```py
def start_request(self):
    yield scrapy.Request(url=get_proxy_url(self.start_urls[0]), callback=self.parse)
```

> This function if defined will be called as the startup function doing the request by scrapy.

> Don't forget to add the proxy domain in the allowed domain list to allow scrapy to send requests to it.

By using the Proxy API, [Faking User Agent](#fake-user-agent) can also be handled by the service provider.

We can also transform the above `get_proxy_url` into a middleware as well. We can choose to implement our own middleware, or use the written one by installing `scrapeops-scrapy-proxy-sdk` using `pip`.




## Middleware

Middlewares are all about **pre processing** the request. To define a middleware, just define `process_request`, `from_crawler` function in the class and include the class name inside the `settings.py`.

```py
@classmethod
def from_crawler(cls, crawler):
    return cls(crawler.settings)

def process_request(self, request, spider):        
        random_user_agent = self._get_random_user_agent()
        request.headers['User-Agent'] = random_user_agent
```

> `@classmethod` decorator is similar to static keyword in CPP, it makes the function a class method which can be called without instantiation. A detail of `from_crawler` can be found here [Classmethod from_crawler in scrapy](https://stackoverflow.com/questions/41046080/classmethod-from-crawler-in-scrapy)