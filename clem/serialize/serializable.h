
class DataStream;

/// 可被序列化
class Serializable
{
public:
	virtual void serialize(DataStream&) = 0;
	virtual void deserialize(DataStream&) = 0;
};

DataStream& operator<<(DataStream& stream, Serializable& s)
{
	s.serialize(stream);
}

DataStream& operator>>(DataStream& stream, Serializable& s)
{
	s.deserialize(stream);
}
