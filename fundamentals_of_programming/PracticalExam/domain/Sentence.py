class Sentence:
    def __init__(self, list_of_words):
        self.__words = list_of_words

    def get_word_by_index(self, index):
        return self.__words[index]

    def exists_word(self, word):
        return word in self.__words

    def get_first_word(self):
        return self.__words[0]

    def get_list_of_words(self):
        return self.__words

    def __str__(self):
        return_string = ''

        for i in range (0, len(self.__words) - 1):
            return_string += str(self.__words[i])
            return_string += ' '
        return_string += self.__words[len(self.__words)-1]

        return return_string
