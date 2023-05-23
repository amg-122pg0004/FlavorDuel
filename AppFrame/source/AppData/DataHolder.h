/*****************************************************************//**
 * \file   DataHolder.h
 * \brief  型消去するデータ所持クラス
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <memory>

namespace AppFrame {
	class DataHolder
	{
	public:
		DataHolder() :_data{ nullptr } {}
		template<typename T>
		void SetData(T data) { _data = std::make_unique<Data<T>>(data); }
		template<typename T>
		T GetData() { return dynamic_cast<Data<T>*>(_data.get())->GetData(); }
	private:
		class DataBase {
		public:
			virtual ~DataBase() {}
		};

		template<typename T>
		class Data : public DataBase {
		public:
			Data(T data) :_data{ data } {}
			T GetData() { return _data; }
		private:
			T _data;
		};
		std::unique_ptr<DataBase> _data;
	};
}