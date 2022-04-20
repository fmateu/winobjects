#include "BaseMemory.h"

BASE::Memory::Memory(int sz) : blksz(sz)
{
	alloc(blksz);
}

void BASE::Memory::alloc(int sz)
{
	block* nio		= new block;
	nio->blk		= new BYTE[sz];
	nio->position	= nio->blk;
	nio->size		= sz;
	mem.push(nio);
}

BYTE* BASE::Memory::Get(int sz)
{
	BYTE* position;

	if ( (LONG)mem.top()->position + sz > (LONG)mem.top()->blk + mem.top()->size )
	{
		if (blksz < sz)
		{
			while ( blksz < sz )
			{
				blksz = blksz*2;
			}
		}
		else
		{
			blksz = blksz*2;
		}	
		alloc(blksz);
	} 
	position = mem.top()->position;
	mem.top()->position = mem.top()->position + sz + 1;
	return position;
}	

void BASE::Memory::Empty()
{	
	while ( !mem.empty()  )
	{
		delete[] mem.top()->blk;
		mem.pop();
	}
}

void BASE::Memory::Clear()
{	
	Empty();
	alloc(blksz);
}

BASE::Memory::~Memory()
{	
	Empty();
}