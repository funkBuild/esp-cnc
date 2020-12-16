import React, { useContext } from 'react';
import { FileContext } from './FileContext';
import { Folder, Download, Trash, FolderPlus } from 'react-feather';
import "./FileDetails.css"

export default () => {
  const {selectedItem, currentPath, openSelectedItem, deleteSelectedItem} = useContext(FileContext);
  const linkUrl = selectedItem ? `http://${process.env.REACT_APP_DEVICE_IP}/fs` + currentPath + '/' + selectedItem.name.toLowerCase() : '';

  return (
    <div className={`file-controls${selectedItem ? " active" : ''}`}>
      <div className="inner-container">
        <div onClick={openSelectedItem}>
          <Folder />
        </div>

        <div>
          { selectedItem && selectedItem.type === 'f' && (
            <a href={ linkUrl }>
              <Download />
            </a>
          )}
        </div>

        <div onClick={deleteSelectedItem}>
          <Trash />
        </div>
      </div>
    </div>
  )
}
