#include <iostream>
#include <iomanip>
#include "ChainedHT.h"
using namespace std;

/**
 * Default constructor.
 */
ChainedHT::ChainedHT() : HashTable() {}

/**
 * Constructor. Initialize each table slot to nullptr.
 */
ChainedHT::ChainedHT(int size) : HashTable(size)
{
   
    for (int i = 0; i < size; i++)
  	{
  		table.push_back(nullptr);
  	}
}

/**
 * Destructor. Delete all the entries in the collision chains.
 */
ChainedHT::~ChainedHT()
{
    
   
}

/**
 * Search for a given table entry. Count the number of probes.
 * @param key the key of the entry to find.
 * @param probe_count the cumulative count of probes.
 * @return a pointer to the entry if found, else return nullptr.
 */
HashEntry *ChainedHT::search(const string& word, int& probe_count)
{
   

    
    int index = hash(word);
	if (table[index] != nullptr)
	{
		HashNode *hashn = table[index];
		while (hashn->entry != nullptr)
		{
			probe_count++;
			if (hashn->entry->word == word)
				return hashn->entry;
			else
			{
				if (hashn->next == nullptr)
					return nullptr;
				hashn = hashn->next;


			}
		}
		probe_count++;
		return nullptr;
	}
	return nullptr;


}

/**
 * If an entry isn't already in the table, enter it with a
 * frequency count of 1. If the entry already exists,
 * update it by incrementing its frequency count by 1.
 * Count the number of probes from the initial search.
 * @param key the key of the entry to enter or update.
 * @return a pointer to the newly entered or updated entry.
 */
HashEntry *ChainedHT::enter(const string& word, int& probe_count)
{
  HashEntry *entry_ptr = search(word, probe_count);

	

	int index = hash(word);

	if (entry_ptr == nullptr && table[index] == nullptr)
	{
		table[index] = new HashNode(new HashEntry(word));
	}
	else if (entry_ptr != nullptr && entry_ptr->word == word)
		entry_ptr->count++;
	else
	{
		HashNode *hashn = table[index];
		while (hashn->next != nullptr)
		{

			hashn = hashn->next;
		}

		hashn->next = new HashNode(new HashEntry(word));
		
		entry_ptr = hashn->entry;
	}
	
	return entry_ptr;
}

/**
 * Print the contents of the hash table.
 
 */
void ChainedHT::dump() const
{
  
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i] != nullptr)
		{

			cout << i << ":" << endl;
			HashNode *hashn = table[i];
			while (hashn->entry != nullptr)
			{
				cout << "    " << hashn->entry->count << "-" << hashn->entry->word << endl;
				if (hashn->next == nullptr)
					break;
				hashn = hashn->next;
			}
		}
	}
}

/**
 * Compute the average chain length.
 */
double ChainedHT::avg_chain_length() const
{
   
	HashNode* hashn ;
	double retVal = 0.0;
	double sum = 0;
	for (int i = 0; i < size;i++)
	{
		if (table[i] != nullptr)
		{
			hashn = table[i];
			sum++;
			while (hashn->next != nullptr)
			{
				hashn = hashn->next;
				sum++;
			}
		}
	}
	
	retVal = sum / size;
	return retVal;

}

