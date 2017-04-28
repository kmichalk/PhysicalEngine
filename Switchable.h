#pragma once

class Switchable
{
	volatile bool enabled_;

public:
	inline Switchable(bool enabled = true):
		enabled_{enabled}
	{
	}

	inline void setEnabled(bool value)
	{
		enabled_ = value;
	}


	inline bool isEnabled() const
	{
		return enabled_;
	}

	inline void toggleEnabled()
	{
		enabled_ = !enabled_;
	}

	virtual ~Switchable();
};
