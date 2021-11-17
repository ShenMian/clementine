// Copyright 2021 ShenMian
// License(Apache-2.0)

#include <cstdint>
#include <string_view>

class Player
{
public:
    enum class State
    {
        Offline,
        Online
    };

    Player() = default;

    Player(uint64_t id, std::string_view name, State state);

    auto getId() const;

    auto getName() const;

    auto getState() const;

    void setState(State state);

private:
    uint64_t         id;
    std::string_view name;
    State            state;
};

inline Player::Player(uint64_t id, std::string_view name, State state)
    : id(id), name(name), state(state)
{
}

inline auto Player::getId() const
{
    return id;
}

inline auto Player::getName() const
{
    return name;
}

inline auto Player::getState() const
{
    return state;
}

inline void Player::setState(State state)
{
    this->state = state;
}
