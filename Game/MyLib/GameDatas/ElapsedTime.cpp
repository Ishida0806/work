//
//		File Name ： ElapsedTime.cpp
//		Production： 2023/9/07
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ElapsedTime.h"

//	定数の初期化
std::unique_ptr<MyLib::ElapsedTime> MyLib::ElapsedTime::m_elapsed = nullptr;