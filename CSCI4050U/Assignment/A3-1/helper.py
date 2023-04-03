import torch
from torchtext.data import get_tokenizer
from torch.utils.data import TensorDataset, DataLoader
from torchtext.vocab import build_vocab_from_iterator
from torchtext.functional import to_tensor, truncate
from torch.utils.data import TensorDataset

#
# use the 'basic_english' tokenizer from the torchtext.data module.
#
tokenize = get_tokenizer('basic_english')


#
# iterate over the `review` column of the dataframe,
# and user the `tokenize` to get the tokens.
#
# returns an iterator of List[str]
#
def iter_review_tokens(df):
    reviews = df['review']
    tokenized_reviews = [tokenize(review) for review in reviews]
    return iter(tokenized_reviews)
        
    
#
# Use the `build_vocab_from_iterator` to construct a
# vocabulary with the following special tokens:
# <pad>, <unk>, <start>
#
def get_vocabulary(df, max_tokens):
    vocabulary = build_vocab_from_iterator(iter_review_tokens(df), max_tokens=max_tokens, specials=['<pad>', '<unk>', '<start>'])
    return vocabulary
    

#
# construct a TensorDataset consisting of
# integer encoding of review words using the given vocabulary, and the
# label (0 for negative, 1 for positive).
#
# Use `truncate` to truncate all token sequences first.
# Use `to_tensor` to perform padding
#
def get_review_dataset(df, voc, max_length):
    reviews = df['review']
    labels = [label for label in df['label'].apply(lambda x: 1 if x == 'positive' else 0)]
    tokenized_reviews = [tokenize(review) for review in reviews]
    truncated_reviews = [truncate(review, max_length) for review in tokenized_reviews]
    encoded_reviews = [voc(review) for review in truncated_reviews]
    print(type(encoded_reviews))
    print("encoded_reviews: ", encoded_reviews[0])
    tensor_reviews = to_tensor(encoded_reviews, padding_value=voc['<pad>'])
    tensor_labels = torch.tensor(labels)
    dataset = TensorDataset(tensor_reviews, tensor_labels)
    return dataset

    
    
