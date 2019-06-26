/*
 * Opis: lepszy set. 
 *   Jeśli chcemy multiseta, to używamy par {val, id}. 
 *   Nie działa z -D\_GLIBCXX\_DEBUG
 * Użycie:
 *   insert(x) dodaje element x
 *   find_by_order(i) zwraca iterator do i-tego elementu
 *   order_of_key(x) zwraca, ile jest mniejszych elementów,
 *   x nie musi być w secie
 */

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<
	T,
	null_type,
	less<T>,
	rb_tree_tag,
	tree_order_statistics_node_update
>;
