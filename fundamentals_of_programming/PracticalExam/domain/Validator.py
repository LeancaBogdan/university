class SentenceValidator:
    def __init__(self):
        pass

    @staticmethod
    def validate(sentence):
        """
        Validates the given sentence and, if any errors occur, they are stored in a ValueError that is raised
        """
        errors = ''

        for word in sentence.get_list_of_words():
            if len(word) < 3:
                errors += "Words need to have at least 3 characters!\n"

        if len(sentence.get_list_of_words()) < 2:
            errors += "Sentence needs to be at least 2 words long!\n"

        if len(errors) > 0:
            raise ValueError(errors)
