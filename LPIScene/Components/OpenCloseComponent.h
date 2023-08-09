#pragma once
// a component that encapsulates an open and closed state (not locked)
class OpenCloseComponent
{
public:
	OpenCloseComponent() = default;

	void SetIsOpen(const bool is_open);
	bool IsOpen() const;
private:
	// open / close state of this component
	bool m_open = false;
};