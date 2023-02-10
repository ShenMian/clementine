#include "entity.hpp"
#include <vector>

namespace ecs
{

template <typename... Ts>
class View
{
public:
	class Iterator
	{
	public:
		Iterator(std::vector<Entity>::iterator it) : iterator_(it) {}

		std::tuple<Ts&...> operator*() const {}

		Iterator& operator++()
		{
			iterator_++;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator it = *this;
			++(*this);
			return it;
		}

		bool operator==(const Iterator& rhs) const noexcept { return iterator_ == rhs.iterator_; };
		bool operator!=(const Iterator& rhs) const noexcept { return iterator_ != rhs.iterator_; };

	private:
		std::vector<Entity>::iterator iterator_;
	};

	View(std::vector<Entity>& entities) : entities_(entities) {}

	Iterator begin() { return entities_.begin(); };
	Iterator end() { return entities_.end(); };

private:
	std::vector<Entity>& entities_;
};

} // namespace ecs
