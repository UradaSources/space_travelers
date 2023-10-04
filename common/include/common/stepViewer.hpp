// Online C++ compiler to run C++ program online
#include <cassert>
#include <iterator>

//  Example:
// 	int foo[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// 	StepViewer<int*> it(foo, 11, 2, 1);

// 	// StepViewer<int> it(foo.begin(), foo.size(), 2, 1, 0);
// 	// StepViewer<int> it(foo.begin(), foo.end() - foo.begin(), 2, 1, 0);

// 	for (; it.vaild(); it.next())
// 		std::printf("next %d\n", it.value());

namespace urd
{
	template<typename It> class StepViewer
	{
	  public:
		using TValue = typename std::iterator_traits<It>::value_type;

		It m_begin;

		int m_size;
		int m_num;
		int m_interval;
		int m_offset;
		int m_pos;

		StepViewer(It begin, int size, int num, int interval, int offset = 0):
			m_begin(begin),
			m_size(size),
			m_num(num),
			m_interval(interval),
			m_pos(0),
			m_offset(offset)
		{
		}
		StepViewer(const StepViewer&) = default;

		int index() const { return m_offset + m_pos; }

		bool vaild() const { return this->index() >= 0 && this->index() < m_size; }

		void restart(int offset = 0)
		{
			m_offset = offset;
			m_pos = 0;
		}

		void next(int step = 1)
		{
			assert(step > 0);

			int groupLen = m_num + m_interval;

			m_pos += step;

			int num = m_pos % groupLen + 1;
			if (num > m_num)
			{
				int nextGroup = m_pos / groupLen + 1;
				m_pos = nextGroup * groupLen;
			}
		}
		TValue value()
		{
			assert(this->vaild());
			return *(m_begin + m_pos + m_offset);
		}
	};
} // namespace urd