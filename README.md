# SnakeLadder
-- Snake Ladder Game --

How to play
- Choose how much player(2-4) at menu.
- Press F11 for fullscreen.

Roll a number to move, First player reach position 39 win. (You'll move back if you move past position 39 depend on how much number you surpass position of 39)
There is 3 special tile in the game:
 - Heal
    - Everytimes step in Heal(green) tile player recover 1HP.
    - There is 1% chance you'll get "Jackpot" which heal player 3HP instead of 1HP.
 - Battle
    - Everytimes you step in Battle(red) tile player need to battle against AI if you lose, you'll lose 1HP and step back 1 position or step forward 1 position if you win.
    - Everytimes you collide with other player you'll force to battle with him/her and loser lose 1HP and step back 1 position.
 - Item
    - Everytimes you step in Item(blue) tile you'll get randomly item as following:
        - Shield: Prevent you from getting battle with player and AI, Upon battle trigger you'll move forward 1 position instead.
        - Boots: Increase you position randomly up to 3 next turn after you rolling a number.
        - Curse: Randomly force some player to step back up to 3 position.(Include player's who obtain this item.)
        - Arena: Randomly battle with someone wherever he/she is.
        - Chaos: Chaos?, wait who's roll next turn again..? (Randomly next turn instead of respectively.)(Include player's who obtain this item.)

When you Hp reach 0, You'll step back 2 positions.
