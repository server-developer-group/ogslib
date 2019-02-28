#pragma once

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃담당자 : Ji-Hyun, LEE (whitewitch@logickorea.co.kr) work in L&K LogicKorea Co., LTD
//┃작성일 : 2008/07/15
//┃
//┃cPointerArrayManager : 데이터를 배열화하여 접근 및 삭제, 삽입에 특화했다.
//┃                       내부 iterator의 사용은 불편한 정도. 접근/삭제/삽입에 특화된 컨테이너
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#define	__THREAD_SAFE

namespace nsContainer
{

namespace nsUniqueKeyContainer
{
	template< class T , s4 expandingSize> 
	class cPointerArrayManager
	{
		friend class PAMIterator;
	private:
		typedef T*		POINTERTYPE;
		POINTERTYPE*	m_ppElementArray;

		s4				m_arrayMax;
		BOOL			m_bDestruct;	//	이 메니져가 포인터를 delete할지를 결정한다.
		std::list<s4>	m_unusedIndex;	//	비사용중인 인덱스 리스트
		std::vector<s4>	m_usedIndex;	//	사용중인 인덱스 리스트

	private:
		BOOL	checkUnusedIndex(s4 _idx)
		{
			std::list<s4>::iterator it = find(m_unusedIndex.begin(),m_unusedIndex.end(), _idx);
			if(it == m_unusedIndex.end())	return FALSE;
			return TRUE;
		}
		BOOL	checkUsedIndex(s4 _idx)
		{
			std::vector<s4>::iterator it = find(m_usedIndex.begin(),m_usedIndex.end(), _idx);
			if(it == m_usedIndex.end())	return FALSE;
			return TRUE;
		}
		BOOL	removeIndex(const s4& _idx)
		{
			std::vector<s4>::iterator it = find(m_usedIndex.begin(),m_usedIndex.end(), _idx);
			if(it == m_usedIndex.end())	return FALSE;
			m_unusedIndex.push_back(*it);
			m_usedIndex.erase(it);
			return TRUE;

		}
		BOOL	isFull()
		{	
			if(!m_unusedIndex.size())		return TRUE;
			return FALSE;
		}
		s4		getNewIndex()
		{
			if(isFull()){	Realloc();	}

			s4		newIdx = *m_unusedIndex.begin();
			m_unusedIndex.pop_front();
			m_usedIndex.push_back(newIdx);

			return newIdx;
		}
		void Realloc(s4 _expandSize = expandingSize)
		{
			m_arrayMax += _expandSize;
			//		m_unusedIndex.reserve(m_arrayMax);
			m_usedIndex.reserve(m_arrayMax);

			POINTERTYPE*		ppTempArray = new POINTERTYPE[ m_arrayMax ];

			if ( m_ppElementArray != NULL ) {
				memcpy( ppTempArray, m_ppElementArray, sizeof( POINTERTYPE ) * m_usedIndex.size() );
				delete [] m_ppElementArray;
			}
			m_ppElementArray = ppTempArray;

			for(s4 i=m_usedIndex.size();i<m_arrayMax;i++)
				m_unusedIndex.push_back(i);
		}


	public:
		cPointerArrayManager( BOOL _bDestruct = FALSE )
			:	m_ppElementArray( NULL ), m_arrayMax( 0 ), m_bDestruct( _bDestruct )
		{
			m_unusedIndex.clear();
			m_usedIndex.clear();
			Realloc();
		}

		~cPointerArrayManager()
		{
			Empty();
			pKILL( m_ppElementArray );
		}

		T& operator() ( const s4& i )	//	내부에 데이타가 없을 때는 문제가 될 수 있다. -o- 추후 변경하자. ㅠ_ㅜ
		{
			assert( i < m_arrayMax );
			return *m_ppElementArray[ i ];
		}

		POINTERTYPE GetItem( const s4& _nIndex )
		{
			//assert( nIndex < arrayNum );
			if(_nIndex >= m_arrayMax ) return NULL;
			return m_ppElementArray[ _nIndex ];
		}

		s4	 AddItem( POINTERTYPE _iItem )
		{
			if( !m_unusedIndex.size() )
			{
				Realloc();
			}

			s4 newIdx = getNewIndex();
			m_ppElementArray[ newIdx ] = _iItem;
			return newIdx;	//	return index
		}

		void Remove( const s4& _nIndex )
		{
			if(!removeIndex(_nIndex))	return;	//	삭제 실패

			if(m_ppElementArray[_nIndex] != NULL)
			{
				if ( m_bDestruct ) {
					delete ( m_ppElementArray[ _nIndex ] );
				}
				m_ppElementArray[ _nIndex ] = NULL;
			}
		}

		//T* Pop( const s4& _nIndex )
		//{
		//	T* pTemp = NULL;

		//	if ( _nIndex < m_arrayCount ) {
		//		pTemp = m_ppElementArray[ _nIndex ];

		//		if ( _nIndex < m_arrayCount - 1 ) {
		//			memcpy( &m_ppElementArray[ _nIndex ], &m_ppElementArray[ _nIndex + 1 ], sizeof( POINTERTYPE ) * ( m_arrayCount - 1 - _nIndex ) );
		//		}

		//		m_arrayCount--;
		//	}

		//	return pTemp;
		//}

		void Empty()
		{
			if ( m_bDestruct ) {
				for ( int i = 0; i < (int)m_usedIndex.size(); i++ ) {
					if( m_ppElementArray[ m_usedIndex[i] ] )
					{
						delete m_ppElementArray[ m_usedIndex[i] ];
						m_ppElementArray[ m_usedIndex[i] ] = NULL;
					}
				}
			}

			m_usedIndex.clear();
			m_unusedIndex.clear();
			for(s4 i=0;i<m_arrayMax;i++)
				m_unusedIndex.push_back(i);
		}

		s4	 GetCount()
		{
			return m_usedIndex.size();
		}

		const s4& GetMax()
		{
			return m_arrayMax;
		}

		class PAMIterator
		{
		public:
			PAMIterator( cPointerArrayManager<T,expandingSize>& _inArray ) : array( _inArray ), m_index( -1 ) {
				++*this;
			}

			void operator++()		{
				++m_index;
				if(m_index >= array.GetCount())
					m_index = array.GetCount()-1;
			}

			void operator--()		{
				--m_index;
				if(m_index <0)
					m_index = 0;
			}

			//void RemoveCurrent()	{
			//	array.Remove( m_index-- );
			//}

			//T* PopCurrent()			{
			//	return array.Pop( m_index-- );
			//}

			s4 GetIndex() const	{
				return array.m_usedIndex[m_index];
			}
			s4 GetIndex(const s4& _idx) const	{
				return array.m_usedIndex[_idx];
			}

			//operator BOOL() const	{
			//	s4 num = array.GetCount();
			//	return m_index < num;
			//}

			T& operator*()	const	{
				return array( GetIndex() );
			}

			T* operator->() const	{
				return &array( GetIndex() );
			}

			T* GetCurrent()	const	{
				return &array( GetIndex() );
			}

			T* GetPrev()	const	{
				s4	value = (m_index ? m_index - 1 : -1);
				if(value != -1)		return &array( GetIndex(value) );
				return NULL;
			}

			T* GetNext()	const	{
				s4	value = ((m_index < (int)array.m_usedIndex.size() - 1) ? (m_index + 1) : (-1));

				if(value != -1)		return &array( GetIndex(value) );
				return NULL;
			}

			void GoFirst()			{
				m_index = 0;
			}

		private:
			cPointerArrayManager<T,expandingSize>&	array;
			s4					m_index;
		};
	};

}	//	end namespace nsUniqueKeyContainer
}	//	end namespace nsContainer