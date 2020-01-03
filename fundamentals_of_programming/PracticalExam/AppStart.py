from repo.repo import SentenceRepository
from controller.controller import SentenceController
from ui.ui import UI


def main():
    sentence_repository = SentenceRepository("repo.txt")
    sentence_controller = SentenceController(sentence_repository)
    ui = UI(sentence_controller)

    ui.main_menu()
    sentence_repository.write_file()


if __name__ == "__main__":
    main()
