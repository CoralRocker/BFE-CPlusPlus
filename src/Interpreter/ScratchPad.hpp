#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

class ScratchPad {
	private:
		uint32_t padId;
		size_t pos;
		std::vector<uint64_t> bf_vec;
		std::vector<size_t> loop_vec;
		std::filesystem::path fpath;	
	public:
		ScratchPad(uint32_t id = 0xFFFF);
		uint32_t getId() { return padId; }
		size_t getPos() { return pos; }

		std::vector<uint64_t>& getBf() { return bf_vec; }
		std::vector<size_t>& getLoop() { return loop_vec; }
		uint64_t& get() { return bf_vec.at(pos); }
		uint64_t& get(size_t where) { return bf_vec.at(where); }
		


		bool loopStart(std::ifstream& f);
		bool loopEnd(std::ifstream& f);

		void next();
		void prev();
		void to_start() { pos = 0; }
		void to_end() { pos = bf_vec.size()-1; }

		void set_path(std::filesystem::path p) { fpath = p; }
		std::filesystem::path& get_path() { return fpath; }

		ScratchPad& operator++ (); // ++ Prefix
		ScratchPad& operator-- (); // -- Prefix
		ScratchPad& operator= (uint64_t x); // Assign current position
		ScratchPad& operator<< (uint64_t x);
		

		void populate(ScratchPad& next); // Load into a new temporary scratchpad
		void depopulate(ScratchPad& next); // Load from a temporary scratchpad
		
		void trimMemory(); // Searches for all of the current value in the memory array and removes it
		
		void printPad();
		void print();
};
