import random
import unittest
from domain.Sentence import Sentence
from domain.Validator import SentenceValidator
from repo.repo import SentenceRepository


class SentenceController:
    """
    Controller
    """
    def __init__(self, sentence_repository):
        """
        Constructor
        :param sentence_repository: The Sentence repo
        """
        self.__sentence_repository = sentence_repository
        self.__sentence_validator = SentenceValidator()

    def add_sentence(self, sentence_string):
        """
        Receives a string, converts it into a Sentence object, validates it and then adds it to the repository
        :param sentence_string: The string representation of the sentence
        :return: The sentence
        :exceptions: ValueError if the sentence is not valid or if the sentence is already stored
        """
        sent = sentence_string.split(' ')
        sentence = Sentence(sent)
        self.__sentence_validator.validate(sentence)
        self.__sentence_repository.add_sentence(sentence)
        return sentence

    def get_random_sentence(self):
        """
        Takes a random sentence from the repository and returns it
        :return: A Sentence object chosen randomly from the repository
        """
        return random.choice(self.__sentence_repository.get_all())

    @staticmethod
    def get_characters_in_sentence(sentence):
        """
        Generates a string with all the characters in a sentence and returns it
        :param sentence: The sentence
        :return: The string of characters
        """
        string = ''

        for word in sentence.get_list_of_words():
            for c in word:
                if c not in string:
                    string += c

        return string

    def get_sentence_for_game_start(self):
        """
        Method that takes a random sentence from the repository and returns it as a string with
         only the first and last character of each word visible, the rest remaining hidden (underscores)
        :return: A string
        :exceptions: ValueError: No sentence in repo
        """
        if len(self.get_all()) == 0:
            raise ValueError("No sentence in repo!")

        random_sentence = self.get_random_sentence()
        printed_sentence = ''
        visible_characters = ''
        for word in random_sentence.get_list_of_words():
            if word[0] not in visible_characters:
                visible_characters += word[0]
            if word[len(word)-1] not in visible_characters:
                visible_characters += word[len(word)-1]

        for word in random_sentence.get_list_of_words():
            for c in word:
                if c not in visible_characters:
                    printed_sentence += '_'
                else:
                    printed_sentence += c
            printed_sentence += ' '

        return printed_sentence

    @staticmethod
    def get_hidden_characters_form_of_sentence(sentence, visible_characters):
        """
        Returns a string with the given characters visible, the rest remaining hidden (underscores), from a sentence
        :param sentence: The sentence
        :param visible_characters: A string containing all the characters that will be visible
        :return: The obtained string
        """
        printed_sentence = ''

        for word in sentence.get_list_of_words():
            for c in word:
                if c not in visible_characters:
                    printed_sentence += '_'
                else:
                    printed_sentence += c
            printed_sentence += ' '

        return printed_sentence

    def get_all(self):
        """
        Getter for the list of sentences from the repository
        :return: The list of sentences from the repository
        """
        return self.__sentence_repository.get_all()


class TestSentenceController(unittest.TestCase):
    def setUp(self):
        self.__sentence_repository = SentenceRepository("test.txt")
        self.__sentence_controller = SentenceController(self.__sentence_repository)

    def test_AddSentence(self):
        self.assertEqual(self.__sentence_controller.add_sentence('ana are alune').get_first_word(), 'ana')
        self.assertNotEqual(self.__sentence_controller.add_sentence('Imi place FPul'), 'imi')

    def test_randomSentence(self):
        self.__sentence_repository.empty()
        self.__sentence_controller.add_sentence('ana are alune')
        self.assertEqual(self.__sentence_controller.get_random_sentence().get_first_word(), 'ana')

    def test_getCharsInSentence(self):
        self.assertEqual(self.__sentence_controller.get_characters_in_sentence(
                Sentence(
                    ['nu', 'mai', 'vreau', 'sa', 'scriu', 'teste']
                )
            ),
            'numaivresct'
        )

    def test_startGame(self):
        self.__sentence_controller.add_sentence('ana are mere')
        self.assertEqual(self.__sentence_controller.get_sentence_for_game_start(), 'a_a a_e me_e ')

    def test_printSentence(self):
        self.assertEqual(self.__sentence_controller.get_hidden_characters_form_of_sentence(
            Sentence(
                ['Diana', 'este', 'frumoasa']
            ),
            'Ditre'),
            'Di___ e_te _r______ '
        )

    def test__getAll(self):
        self.__sentence_controller.add_sentence('ana are mere')
        self.assertEqual(self.__sentence_controller.get_all()[0].get_first_word(), 'ana')
