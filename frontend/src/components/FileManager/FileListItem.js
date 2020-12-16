import React, { useContext, useCallback } from 'react';
import { bytesToString } from '../../util/conversions';
import { FileContext } from './FileContext';

import "./FileListItem.css"

export default function FileListItem(props){
  const { selectedItem, setSelected } = useContext(FileContext);
  const { item } = props;

  const isSelected = item === selectedItem;

  const handleSelect = useCallback((e) => {
    e.stopPropagation()
    setSelected(item)
  }, [item])

  const icon = item.type === 'd' ? (
    <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
      <path d="M22 19a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h5l2 3h9a2 2 0 0 1 2 2z">
      </path>
    </svg>
  ) : (
    <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
      <path d="M13 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V9z"></path>
      <polyline points="13 2 13 9 20 9"></polyline>
    </svg>
   )

  return (
    <div className={`FileListItem ${isSelected ? " selected" : ''}`} onClick={handleSelect}>
      <span>{ icon }</span>
      <span>{ item.name }</span>
      <span>{ item.type === 'f' && bytesToString(item.size) }</span>
    </div>
  )
}
