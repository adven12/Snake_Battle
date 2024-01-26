#pragma once

template <typename T>
T ChangeMainMenuItemUp(T newItem, const T firstItem, const T lastItem) 
{
	newItem = (newItem == firstItem) ? lastItem : static_cast<T>(static_cast<int>(newItem) - 1);
	return newItem;
}
template <typename T>
T ChangeMainMenuItemDown(T newItem, const T firstItem, const T lastItem) 
{
	newItem = (newItem == lastItem) ? firstItem : static_cast<T>(static_cast<int>(newItem) + 1);
	return newItem;
}

template <typename T>
struct Vector2 
{
	T x;
	T y;
};
template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right) 
{
	return left.x == right.x && left.y == right.y;
}
