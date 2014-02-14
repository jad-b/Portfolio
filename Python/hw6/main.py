#!/usr/bin/python
__author__ = "Jeremy Dobbins-Bucklad"
__course__ = "CS671"

import string
from collections import Counter

alphabet = string.lowercase

def encode(message,shift=13):
    """Encodes the given 'message' string by shifting letters by a given 
    amount. Currently modifies the message to only work on lowercase letters.
    """
    if shift > 26 or shift < -26:
        raise ValueError
    msg = []
    for c in string.lower(message):
        if c in string.lowercase:
            msg.append(alphabet[(alphabet.index(c)+shift)%len(alphabet)])
        else:
            msg.append(c)
    return ''.join(msg)

def tryShifts(message):
    """Attempts to decode the message by shifting it to match most frequently
    used English letters. For example, if 'a' is the most frequently used English
    letter, and the message has 't' as the most frequent, it would shift the 
    message's characters by the difference between t and a."""
    freqLtrs = 'etaoinshrdlucmfwypvbgkqjxz'
    msg = string.lower(message)
    # Count the frequency of each letter
    cnt = Counter()
    for c in msg:
        if c in string.lowercase:
            cnt[c] += 1

    highest_freq = cnt.most_common(1)[0][0]
    # print highest_freq
    for c in freqLtrs:
        shift = alphabet.index(c) - alphabet.index(highest_freq)
        print c, highest_freq, shift
        yield encode(msg,shift)   



# Tests
# g = tryShifts("why hello there")
# while True:
#     try:
#         print g.next()
#     except StopIteration:
#         print "Done"
#         break

class Trie:
    """The Trie class stores words and word counts as dicts of (char,(int,dict)) 
    key/value tuples. 
    key, char: Char stored at this depth (in the word)
    value, int: Number of times the word formed with the key char as the terminal
    character has been found.
    value, dict: Next level of suffix characters found after the current char
    """
    def __init__(self):
        self.total = 0
        self.root = {}

    def build(self,word_list):
        for w in word_list:
            self.add(w)

    def add(self,word):
        """Adds words to the Trie by iteratively placing the head character
        of the string into descending levels of the Trie.
        """
        if word is '':
            raise ValueError
        lvl = self.root
        for i,c in enumerate(word):
            try: # Check if entry for c exists
                val = lvl[c]
            except KeyError:
                val = lvl[c] = (0,None) # Setup new entry

            if i+1 < len(word): # More to come
                if lvl[c][1] is None:
                    lvl[c] = (lvl[c][0],{}) # Instantiate a new dict
                lvl = lvl[c][1] # Update lvl 'pointer'
        else: # Up word count on terminating character
            # lvl[c] = (lvl[c][0]+1,lvl[c][1]) 
            self.total += 1

    def __contains__(self,word):
        lvl = self.root
        for i,c in enumerate(word):
            try: 
                lvl[c]
            except KeyError: # Char not found
                return False
            if i+1 < len(word): # If more to go
                if lvl[c][1] is None: # Trie stops short
                    return False
                else:
                    lvl = lvl[c][1]
        else:
            print "Trie contains "+word
            return True

    def update(self,word):
        lvl = self.root
        for i,c in enumerate(word):
            try: 
                lvl[c]
            except KeyError: # Char not found
                return 0
            if i+1 < len(word): # If more to go
                if lvl[c][1] is None: # If trie stops short; error
                    return 0
                else: # Goto next level down
                    lvl = lvl[c][1]
        else: # Success
            lvl[c] = (lvl[c][0]+1,lvl[c][1])
            print "{}: {}".format(word,lvl[c][0])

    def count(self,word):
        lvl = self.root
        for i,c in enumerate(word):
            try: 
                lvl[c]
            except KeyError: # Char not found
                return 0
            if i+1 < len(word): # If more to go
                if lvl[c][1] is None: # Trie stops short
                    return 0
                else:
                    lvl = lvl[c][1]
        else:
            return lvl[c][0]

    def __repr__(self):
        return "Trie: "+str(self.total)

    def reset(self):
        self.root.clear()
        self.total = 0

def decode(message,dictfilename="/usr/share/dict/words"):
    """Searches for a valid decoding of the given message.
    Begins by building its Trie from a file dictionary.
    Various decodings are then attempted on the message until
    one is composed of greater than half valid words, according
    to our Trie."""
    def countValidWords(t,m):
        """Tallies the number of valid words in the message"""
        cnt = 0
        for w in [s.strip(string.punctuation) for s in m.split(" ")]:
            if w in t:
                cnt += 1
        return cnt

    t = Trie()
    # Build Trie from file
    with open(dictfilename) as f:
        for line in f:
            for w in line.split(" "):
                t.add(string.lower(w.strip(string.punctuation)))
    # Prepare message for parsing
    msg = [s.strip(string.punctuation) for s in message.split(" ")]
    msg_len = len(msg)
    # Try various decodings
    g = tryShifts(message)
    m = next(g,None)
    # Iterate through decodings until no more or valid one is found
    while m is not None and countValidWords(t,m) <= (msg_len/2):
        m = next(g,None)

    if m is None: # Never found a valid decoding
        return None
    else:
        for w in [s.strip(string.punctuation) for s in m.split(" ")]:
            t.update(w)
        return (m,t)







quote = "Quite frankly my dear, I don't give a damn"
quote = [s.strip(string.punctuation) for s in quote.split(" ")]
t = Trie()
t.build(quote)

print decode(encode("elizabeth, you tramp",19))





