#include "ai.h"

ai::ai(QObject *parent) : QObject(parent)
{

}


/* This depends on
1) Whether the AI is X or O
2) What turn is it
3) The current state of the board

For example

let's say that the board has an X in the middle.
So AI is O,
it's turn 2
and the state is as said before.

Now the AI will want to return either one of 0, 2, 6, 8.

Or take another example.
AI is O
it's turn 6
and it looks like

OXO
X
 X

Then AI will definitely want to prevent X from getting the winning move.

This function will return a single integer, which corresponds to one of 0...8, which is
the best move.

Algorithm
1) Check for a winning move, if so, go for it.
2) Check for an opponent winning move, if so, block it.
3) Otherwise, do some common sense stuff.
4) All else fails, pick a random number.

*/
int ai::computeBestMove()
{


    return 0;
}
