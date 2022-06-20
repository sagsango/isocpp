/* # move constructor
 *
 * ## move semantics
 *
 * Useful in situations where a class heap allocated data.
 *
 * Made possible by C++11 rvalue references.
 *
 * Basic idea: when copying from an rvalue, it is not necessary to make an expensive copy of it:
 * it suffices to acquire its data via swap, and leave it on a valid state (via a default constructor for example).
 *
 * This is true because the rvalue passed to a copy constructor cannot be seen.
 *
 * Value reference allows to overload the copy constructor based not on type,
 * but on the fact that a value is an rvalue or an lvalue!
 *
 * No change must be done to the copy and swap idiom for move semantics to work for the assignment operator,
 * since in C++11 `int i = rvale` calls a move consttuctor on `i` while `int i = lvalue` calls a copy constructor.
 *
 * ## Bibliography
 *
 * - http://stackoverflow.com/questions/3106110/what-is-move-semantics
 * - http://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used
 */

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    // TODO example
#endif
}
