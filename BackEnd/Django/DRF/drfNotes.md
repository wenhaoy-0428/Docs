# Django Rest Framework

DRF is a framework of Django that provides an abstraction of **API** for not only Web APP, but Mobile APP.


# Requests

For **Get** requests, data are accessed through `request.query_param`, also axios has to use 

```js
axios.get('/user', {
    params: {
      ID: 12345
    }
  })
// or
axios.get('/user?ID=12345')
  .then(function (response) {
    // handle success
    console.log(response);
  })
  .catch(function (error) {
    // handle error
    console.log(error);
  })
  .finally(function () {
    // always executed
  });
```


For **Post** requests, data are accessed through `request.data`




# [Serializer](https://www.django-rest-framework.org/api-guide/serializers/)

Serializer allows to serialize `JSON` to validated python format or reverse. 


Use `many=True` attribute when calling the serializer if serializing a list of data.


### Standard Serializer

A Standard serializer is derived from `serializers.Serializer`. It gives us more flexibility to override more. However, we have to define each fields again in addition to model's fields. 

A typical example is shown as follows, [code source](https://www.django-rest-framework.org/tutorial/1-serialization/).

```python
class Snippet(models.Model):
    created = models.DateTimeField(auto_now_add=True)
    title = models.CharField(max_length=100, blank=True, default='')
    code = models.TextField()
    linenos = models.BooleanField(default=False)
    language = models.CharField(choices=LANGUAGE_CHOICES, default='python', max_length=100)
    style = models.CharField(choices=STYLE_CHOICES, default='friendly', max_length=100)

    class Meta:
        ordering = ['created']

from rest_framework import serializers
from snippets.models import Snippet, LANGUAGE_CHOICES, STYLE_CHOICES


class SnippetSerializer(serializers.Serializer):
    id = serializers.IntegerField(read_only=True)
    title = serializers.CharField(required=False, allow_blank=True, max_length=100)
    code = serializers.CharField(style={'base_template': 'textarea.html'})
    linenos = serializers.BooleanField(required=False)
    language = serializers.ChoiceField(choices=LANGUAGE_CHOICES, default='python')
    style = serializers.ChoiceField(choices=STYLE_CHOICES, default='friendly')

    def create(self, validated_data):
        """
        Create and return a new `Snippet` instance, given the validated data.
        """
        return Snippet.objects.create(**validated_data)

    def update(self, instance, validated_data):
        """
        Update and return an existing `Snippet` instance, given the validated data.
        """
        instance.title = validated_data.get('title', instance.title)
        instance.code = validated_data.get('code', instance.code)
        instance.linenos = validated_data.get('linenos', instance.linenos)
        instance.language = validated_data.get('language', instance.language)
        instance.style = validated_data.get('style', instance.style)
        instance.save()
        return instance

```

Inside the serializer class, each fields (e.g. `id`, `title`) are defined to be serialized/deserialized. Thus, the input data (`JSON`) has to contain such fields.

`create` and `update` are used when instanced is saved by calling `serializer.save()`.

> If we only care about serialize data into `JSON` (AKA deserialization), `create` and `update` can be omitted.


#### Serialize Objects

Don't stay in a narrow mind that serializer is used only for models, we can fetch data from model and reassemble into a new object/class then use standard serializer to format.

```python
class DetailEntry():
    def __init__(self, tag, link, value):
        self.tag = tag
        self.link = link
        self.value = value

class ReviewEntry():
    def __init__(self, word, entries):
        self.word = word
        self.entries = entries
    
class GetReview(APIView):
    
    def get(self, request, format=None):
        # get current user
        currentUser = User.objects.get(id=request.user.id)

        records = Record.objects.filter(user_id=currentUser)

        reviewEntries = []
        for record in records:
            word = record.word_id
            quotes = Quote.objects.filter(record_id=record)
            
            detailEntries = []
            for quote in quotes:
                tag = quote.tagAssignment_id
                link = quote.link
                value = quote.value
                detailEntries.append(DetailEntry(tag, link, value))

            reviewEntries.append(ReviewEntry(word, detailEntries))
        s = ReviewSerializer(reviewEntries, many=True)
        
        return Response(s.data)


class QuoteSerializer(serializers.Serializer):
    tag = serializers.CharField(max_length=30)
    link = serializers.URLField()
    value = serializers.CharField(max_length=300)


class ReviewSerializer(serializers.Serializer):
    word = serializers.CharField(max_length=150)
    entries = QuoteSerializer(many=True)
    
```


### Model Serializer

Model Serializer simplifies the majority of code, that we only need to specify model and field names

```python
class SnippetSerializer(serializers.ModelSerializer):
    class Meta:
        model = Snippet
        fields = ['id', 'title', 'code', 'linenos', 'language', 'style']
```

> Note that, these field names have to be the same as the model's. You can have less fields, which only affects:
> 1. When serializing `from Python to JSON`, unspecified fields will be omitted.
> 2. When serializing `from JSON to Python`, only specified filed will be kept and validated. Note that missing fields won't cause validation problem but may cause save problem as violating some of `Non NULL constraints`


#### [Relation Serializer and nesting](https://www.django-rest-framework.org/api-guide/relations/)

Some model has relational fields, such as foreign keys. 


* For the model that has the foreign, (the `many` in a `One to Many` relationship), such field can be directly accessed. 

```python

class Word(models.Model):
    value = models.CharField(max_length=150, unique=True)

    def __str__(self):
        return self.value


class Record(models.Model):
    user_id = models.ForeignKey(User, on_delete=models.CASCADE)
    word_id = models.ForeignKey(Word, on_delete=models.CASCADE)

    def __str__(self):
        return f'{self.user_id}-{self.word_id}'


class RecordSerializer(serializers.ModelSerializer):
    class Meta:
        model = Record
        fields = ['user_id', 'word_id']

```

However, the above serializer will generate JSON that contains the `primary key`. One way is to display the `__str__` method of the referenced model by using [StringRelatedField](https://www.django-rest-framework.org/api-guide/relations/#stringrelatedfield)

```python
class RecordSerializer(serializers.ModelSerializer):
    word_id = serializers.StringRelatedField()
    class Meta:
        model = Record
        fields = ['user_id', 'word_id']
```

> Also, we can use [to_representation](https://www.django-rest-framework.org/api-guide/relations/#custom-relational-fields) to customize exactly how the field is going to be displayed.

```python

class TagAssignmentToTagField(serializers.RelatedField):
    """ A custom relational filed that is used by @link QuoteSerializer
    """

    def to_representation(self, value):
        return f'{value.tag_id}'


class QuoteSerializer(serializers.ModelSerializer):
    tag = TagAssignmentToTagField(source='tagAssignment_id', read_only=True)

    class Meta:
        model = Quote
        fields = ['pk', 'link', 'value', 'tag']

```

* For models are referenced, and try to access the related model, add `_set` lookup option. (e.g. `field_name_set` ) or add `related_name` in the model.

The [entire official documentation of relational serializing](https://www.django-rest-framework.org/api-guide/relations/#stringrelatedfield) is based on the reverse relations



In the above cases, we're accessing the related model as a single field of the current model. Sometimes, we also want to nest the whole related model inside the current model. Thus, we'll write a serializer for the child model called child serializer then specify the filed in parent serializer equal to the child serializer

```py

class QuoteSerializer(serializers.ModelSerializer):
    tag = TagAssignmentToTagField(source='tagAssignment_id', read_only=True)

    class Meta:
        model = Quote
        fields = ['pk', 'link', 'value', 'tag']


class RecordSerializer(serializers.ModelSerializer):
    word = serializers.StringRelatedField(source='word_id')
    quotes = QuoteSerializer(many=True, read_only=True)

    class Meta:
        model = Record
        fields = ['pk', 'word', 'date_added', 'mastery', 'quotes']

    def to_representation(self, instance):
        ret = super().to_representation(instance)
        # update the representation of mastery so that it shows decayed value since last reviewed.
        ret['mastery'] = utils.calcDecayedMastery(instance)
        return ret

```

> Note, nested serializers are **read-only**, meaning we can only get Models to Json, but can create Model from json. To make writable nested serializer, we have to explicitly write the create process in the `.create` method of the root serializer. We **can't** have nested `create`, meaning it's not allowed to let parent'create method call children't create method.


#### Permissions




 
  