#pragma once

class Closeable
{
public:
	virtual bool isClosed() const abstract;
	virtual void close() abstract;

	virtual ~Closeable();
};
