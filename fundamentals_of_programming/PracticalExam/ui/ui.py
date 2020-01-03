class UI:
    def __init__(self, sentence_controller):
        self.__sentence_controller = sentence_controller

    @staticmethod
    def read_command(prompt_message):
        print(prompt_message)

        try:
            return int(input("Enter a command: "))

        except ValueError as ve:
            print(ve)
            return

    def main_menu(self):
        menu_string = ''
        menu_string += 'Main menu\n'
        menu_string += '\t1. Add a sentence\n'
        menu_string += '\t2. Start game\n'
        menu_string += '\t3. Play game\n'
        menu_string += '\t0. Exit\n'

        while True:
            command_list = {0: self.__exit,
                            1: self.__add_sentence,
                            2: self.__start_game,
                            3: self.__play_game}
            command = self.read_command(menu_string)

            if command in command_list.keys():
                if command == 0:
                    return
                else:
                    command_list[command]()

            else:
                print("Invalid command!")

    def __add_sentence(self):
        string = input("Please enter the sentence: ")

        try:
            self.__sentence_controller.add_sentence(string)

        except ValueError as ve:
            print(ve)

    def __start_game(self):
        try:
            print(self.__sentence_controller.get_sentence_for_game_start())

        except ValueError as ve:
            print(ve)

    def __play_game(self):
        if len(self.__sentence_controller.get_all()) == 0:
            print("No sentence in repo!")
            return

        random_sentence = self.__sentence_controller.get_random_sentence()
        characters_in_sentence = self.__sentence_controller.get_characters_in_sentence(random_sentence)
        visible_characters = ''
        hangman_counter = 0
        hangman_word = 'hangman'
        won = False

        for word in random_sentence.get_list_of_words():
            visible_characters += word[0]
            visible_characters += word[len(word) - 1]
        print(self.__sentence_controller.get_hidden_characters_form_of_sentence(random_sentence, visible_characters))

        while not won and hangman_counter < 7:
            user_guess = input("User guess: ")
            if not self.verify_input(user_guess, visible_characters, characters_in_sentence):
                hangman_counter += 1
                print(hangman_word[0:hangman_counter])
            else:
                visible_characters += user_guess
                printed_sentence = self.__sentence_controller.get_hidden_characters_form_of_sentence(random_sentence, visible_characters)
                if '_' not in printed_sentence:
                    won = True
            print(self.__sentence_controller.get_hidden_characters_form_of_sentence(random_sentence, visible_characters))

        if self.end_game(hangman_counter, won):
            return

    def verify_input(self, user_input, visible_characters, characters_in_sentence):
        if type(user_input) != str or len(user_input) != 1:
            print("Invalid input!")
            return False

        elif user_input in visible_characters:
            print("Character already given!")
            return False

        elif user_input not in characters_in_sentence:
            print("Character not in the given sentence!")
            return False

        return True

    @staticmethod
    def end_game(hangman_counter, won):
        if hangman_counter == 7:
            print("You lost!")
            return True

        if won:
            print("You won!")
            return True

    def __exit(self):
        pass
