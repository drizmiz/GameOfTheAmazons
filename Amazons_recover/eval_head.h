
#pragma once

#include "game.h"

namespace eval_adj	// evaluation adjusted
{
	using namespace std;
	using namespace amz;

	ofstream ofs("records.log");

	void unexpect(bool condition, string msg) {
#ifdef _DEBUG
		if (condition) {
			ofs << "unexpected condition: " << msg << endl;
#ifdef THROW_EXCEPTION 
			throw exception(msg.c_str());
#endif
		}
#endif
	}
	inline void append_log(const string& msg, bool always = false) {
#ifdef _DEBUG
		if (always) ofs << msg << endl;
		else {

			ofs << msg << endl;

		}
#endif
	}
	class player {
	public:
		using single_player = std::array<std::tuple<len_t, len_t>, 4>;
		player(bool is_black, const chess_status& cs) :_is_black(is_black), _cs(cs) {}
		const single_player self() const {
			return _is_black ? _Transform_4_to_ij(_cs.get_black()) : _Transform_4_to_ij(_cs.get_white());
		}
		const single_player opponent() const {
			return (!_is_black) ? _Transform_4_to_ij(_cs.get_black()) : _Transform_4_to_ij(_cs.get_white());
		}
		bool id() const { return !_is_black; }
	private:
		bool _is_black;
		const chess_status& _cs;
	};
	class teil
	{
	private:
		bool _is_empty;
	public:
		teil(bool i) :_is_empty(i) {}
		bool is_empty() const { return _is_empty; }
	};
	class board {
	public:
		board(const chess_status& cs) :_cs(cs) {}
		const teil operator()(len_t x, len_t y) const {
			return _locate_teil(x, y);
		}
		void _output_board() {
			_Debug_paint(_cs);
			// append_log(str, true);
		}
	private:
		const teil _locate_teil(len_t x, len_t y) const {
			return !(_cs.get_all() & mask(x, y));
		}
		/*
		void _count_amazons() const {
			size_t w = 0, b = 0;
			for (int i = 0; i < 8; ++i)
				for (int j = 0; j < 8; ++j)
					if (_map[i][j].is_white()) ++w;
					else if (_map[i][j].is_black()) ++b;
			unexpect(w < 4, "white amazons less than 4");
			unexpect(b < 4, "black amazons less than 4");
		}
		*/
	private:
		const chess_status& _cs;
	};
}