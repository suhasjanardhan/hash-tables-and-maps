#include "QuadraticProbeHT.h"
using namespace std;

QuadraticProbeHT::QuadraticProbeHT() : OpenAddressHT(), odd(1) {}
QuadraticProbeHT::QuadraticProbeHT(int size) : OpenAddressHT(size), odd(1) {}

QuadraticProbeHT::~QuadraticProbeHT() {}

/**
 * Search for a given table entry. Overrides OpenAddressHT::search().
 * @param key the key of the entry to find.
 * @param probe_count the cumulative count of probes.
 * @return the hash table index of the entry if found, else of an empty slot.
 */
int QuadraticProbeHT::search(const string& key, int& probe_count)
{
    
	int index = hash(key);
	
	QuadraticProbeHT qa(size);


	while (qa.get_entry(index) != nullptr)
	{
		if (qa.get_entry(index)->word == key)
		{
			probe_count++;
			return index;
		}
		else
		{
			probe_count++;
			odd ++ ;
			index = next_index(index);
			
		}
	}
	probe_count++;
	return index;
}

/**
 * Compute the index of the next hash table slot away from
 * the current slot to check. For quadratic probing, the ith probe
 * checks the slot that is i-squared away from the home slot
 * computed by hash(). Use the formula n^2 = 1 + 3 + 5 + ... + 2n-1.
 * Use private member variable odd to compute the successive squares.
 * @param index the index of the current slot.
 * @return the index of the next slot.
 */
int QuadraticProbeHT::next_index(int index)
{
    
	int sqrt = 0;
	for (int i = 0; i < 2 * odd - 1; i++)         //2n-1
	{
		sqrt = sqrt + 1;
	}
	return (index + sqrt);
}
