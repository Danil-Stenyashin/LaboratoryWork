#include "include/DialogueManager.h"
#include "include/utils.h"


namespace fs = std::filesystem;
const std::string DIALOGUE_FOLDER = "game/dialogues/";


void DialogueManager::saveDialogueProgress(const std::string& dialogueId) {
    std::filesystem::create_directories("game/saves");
    
    std::ofstream file(DIALOGUE_SAVE_PATH);
    if (file.is_open()) {
        file << dialogueId;
        log.logEvent("Сохранен прогресс диалога: " + dialogueId);
    } else {
        log.logEvent("Ошибка сохранения диалога в " + DIALOGUE_SAVE_PATH);
    }
}


std::string DialogueManager::loadDialogueProgress() {
    std::ifstream file(DIALOGUE_SAVE_PATH);
    if (file.is_open()) {
        std::string savedDialogue;
        std::getline(file, savedDialogue);
        return savedDialogue.empty() ? "start" : savedDialogue;
    }
    return "start"; // Возвращаем стартовый диалог по умолчанию
}

void DialogueManager::saveDialogueState(const std::string& dialogueId) {
    std::ofstream file("game/saves/dialogue_state.txt");
    if (file.is_open()) {
        file << dialogueId;
    }
}


std::string DialogueManager::loadDialogueState() {
    std::ifstream file("game/saves/dialogue_state.txt");
    if (file.is_open()) {
        std::string savedId;
        std::getline(file, savedId);
        return savedId.empty() ? "start" : savedId;
    }
    return "start";
}

void DialogueManager::loadDialogue(const std::string& dialogueName) {
    std::string filePath = DIALOGUE_FOLDER + dialogueName + ".txt";
    if (!fs::exists(filePath)) return;

    std::ifstream file(filePath);
    if (!file.is_open()) return;

    std::string line;
    std::vector<std::string> choices;
    int textSpeed = 30;

    while (std::getline(file, line)) {
        if (line.rfind("speed=", 0) == 0) {
            textSpeed = std::stoi(line.substr(6));
            continue;
        }
        if (line[0] == '#') break;
        print(line, textSpeed);
    }

    while (std::getline(file, line)) {
        if (line[0] == '#') break;
        choices.push_back(line);
    }

    for (size_t i = 0; i < choices.size(); ++i) {
        print("(" + std::to_string(i+1) + ") " + choices[i].substr(5));
    }

    int choice = handleInput(1, choices.size());
    log.logEvent("Выбран вариант: " + choices[choice-1].substr(5));
    save.saveProgress(choices[choice-1].substr(0, 5));
    loadDialogue(choices[choice-1].substr(0, 5));
    
    saveDialogueState(choices[choice-1].substr(0, 5));
}
