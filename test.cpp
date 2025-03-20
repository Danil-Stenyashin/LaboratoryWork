#include <gtest/gtest.h>
#include "Character.h"
#include "Player.h"

// Тест конструктора Character
TEST(CharacterTest, Constructor) {
    Character character("Алиса", 100, 50);
    EXPECT_EQ(character.getName(), "Алиса");
    EXPECT_EQ(character.getHealth(), 100);
    EXPECT_EQ(character.getStamina(), 50);
}

// Тест сеттеров Character
TEST(CharacterTest, Setters) {
    Character character("Алиса", 100, 50);
    character.setName("Лена");
    character.setHealth(80);
    character.setStamina(40);

    EXPECT_EQ(character.getName(), "Лена");
    EXPECT_EQ(character.getHealth(), 80);
    EXPECT_EQ(character.getStamina(), 40);
}

// Тест конструктора Player
TEST(PlayerTest, Constructor) {
    Player player("Коля", 100, 100);
    EXPECT_EQ(player.getName(), "Коля");
    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getStamina(), 100);
}

// Тест метода makeChoice (здесь просто проверяем, что код компилируется)
TEST(PlayerTest, MakeChoice) {
    Player player("Коля", 100, 100);
    player.makeChoice(1); // Проверка на выполнение метода (он просто выводит текст)
}

// Основная функция тестирования Google Test
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

