from domain.Sentence import Sentence
import unittest


class SentenceRepository:
    """
    Repository for the sentences
    """
    def __init__(self, filename):
        """
        Constructor
        :param filename: The name of the file where the repository will be stored
        """
        self.__sentences = []
        self.__filename = filename
        self.read_file()

    def get_sentence_by_index(self, index):
        """
        Getter for a sentence by its index in the list
        :param index: The index
        :return: The sentence
        """
        return self.__sentences[index]

    def add_sentence(self, sentence):
        """
        Adds a sentence to the repository, after checking if it isn't already stored
        :param sentence: The sentence to be added to the repository
        :return: -
        :exception: ValueError: Sentence already stored in the repository!
        """
        if len(self.get_all()) > 0:
            for sent in self.get_all():
                ok = 0
                for word1 in sent.get_list_of_words():
                    if not sentence.exists_word(word1):
                        ok = 1
                if ok != 1:
                    raise ValueError("Sentence already stored in the repository!")

        self.__sentences.append(sentence)

    def get_all(self):
        """
        Getter for the list of sentences in the repository
        :return: The list of sentences in the repository
        """
        return self.__sentences

    def read_file(self):
        """
        Reads all the sentences from a txt file, each sentence on a line, words separated by spaces
        :return: -
        :exception: IOError, EOFError
        """
        f = None

        try:
            f = open(self.__filename, 'r')
            line = f.readline()

            while line != '':
                line = line.strip('\n').split(' ')
                sentence = Sentence(line[:])
                self.add_sentence(sentence)
                line = f.readline()

        except IOError as ie:
            return ie
        except EOFError as ee:
            return ee

        finally:
            if f:
                f.close()

    def write_file(self):
        """
        Writes all the sentences in the repository in the repository file, each sentence on a line, words separated by space
        :return: -
        :raises: IOError, EOFError
        """
        f = None

        try:
            f = open(self.__filename, 'w')
            all_sentencess_string = ''
            for sentence in self.get_all():
                current_sentence_string = str(sentence)
                current_sentence_string += '\n'
                all_sentencess_string += current_sentence_string
            f.write(all_sentencess_string)

        except IOError as ie:
            print(ie)
        except EOFError as ee:
            return print(ee)

        finally:
            f.close()

    def empty(self):
        """
        Empties the list of stored sentences
        :return: -
        """
        self.__sentences.clear()


class TestSentenceRepository(unittest.TestCase):
    def setUp(self):
        self.sentence_repository = SentenceRepository("test.txt")
        if len(self.sentence_repository.get_all()) == 0:
            self.sentence_repository.add_sentence(Sentence(['test', 'abc', 'defg']))
            self.sentence_repository.add_sentence(Sentence(['Test', '123', 'hgfb']))

    def test_addSentence_getSentenceByIndex(self):
        self.assertEqual(self.sentence_repository.get_sentence_by_index(0).get_first_word(), 'test')
        self.assertNotEqual(self.sentence_repository.get_sentence_by_index(1).get_first_word(), 'test')
        self.assertEqual(self.sentence_repository.get_sentence_by_index(1).get_first_word(), 'Test')

    def test_writeFile_getAll(self):
        self.sentence_repository.write_file()
        self.sentence_repository.empty()
        self.sentence_repository.read_file()
        self.assertEqual(self.sentence_repository.get_all()[0].get_first_word(), 'test')
