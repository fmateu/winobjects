#pragma once
#include <windows.h>
#include <cstdlib>
#include <stack>
#include "macros.h"

namespace BASE
{
	class Memory
	{
		private:
			int blksz;
			struct block
			{
				LONG size;
				BYTE* blk;
				BYTE* position;
			};
			std::stack<block*> mem;
			void alloc(int sz);
			void Empty();
		public:
			Memory(int sz = 1024);
			void Clear();
			BYTE* Get(int sz);
			~Memory();
	};
}