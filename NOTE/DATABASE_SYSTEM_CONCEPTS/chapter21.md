# CHAPTER 21 Information Retrieval



The term `information retrieval` generally refers to the querying of unstructured textual data.

The field of `information retrieval` has developed in parallel with the field of database.

There are several differences between this model and the models used in traditional database systems:

- Database systems deal with several operations that are not addressed in information-retrieval systems.
- Information-retrieval systems deal with several issues that have not been addressed adequately in database systems.

In `full text` retrieval, all the words in each document are considered to be keywords.

One way of measuring $TF(d, t)$, the relevance of a document $d$ to a term $t$, is:
$$
TF(d, t) = log(1 + \frac{n(d, t)}{n(d)})
$$
, where $n(d)$ denotes the number of terms in the document and $n(d, t)$ denotes the number of occurrences of term $t$ in the document $d$.

In the information retrieval community, the relevance of a document to a term is referred to as `term frequency (TF)`, regardless of the exact formula used.

`Inverse document frequency (IDF)` define as:
$$
IDF(t) = \frac{1}{n(t)}
$$
, where $n(t)$ denotes the number of documents (among those indexed by the system) that contain the term $t$. The `relevance` of a document $d$ to a set of terms $Q$ is then defined as:
$$
r(d, Q) = \sum_{t \in Q} TF(d, t) * IDF(t)
$$
, this measure can be further refined if the user is permitted to specify weights $w(t)$ for terms in the query, in which case the user-specified weights are also taken into account by multiplying $TF(t)$ by $w(t)$ in the above formula.

More generally, the similarity of documents is defined by the `cosine similarity` metric. Let the terms occurring in either of the two documents be $t_1, t_2, ..., t_n$. Let $r(d, t) = TF(d, t) * IDF(t)$. Then the cosine similarity metric between documents $d$ and $e$ is defined as:
$$
\frac{\sum_{i=1}^{n}r(d, t_i)r(e, t_i)}{\sqrt{\sum_{i=1}^{n}r(d, t_i)^2} \sqrt{\sum_{i=1}^{n}r(e, t_i)^2}}
$$
, you can easily verify that the cosine similarity metric of document with itself is 1, while that between two documents that do not share any terms is 0.

`Search engine spamming` refers to the parctice of creating Web pages, or sets of Web pages, designed to get a high relevance rank for some queries, even though the sites are not actually popular sites.

`Information-extraction` systems convert information from textual form to a more structured form.

`Question answering` systems attempt to provide direct answers to questions posed by users.



## Summary

TODO