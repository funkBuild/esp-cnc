import React, { useEffect, useState, useRef, useCallback } from 'react';

import ApiClient from '../../models/ApiClient';

import { useJob } from "../../hooks/useJob"

const FileContext = React.createContext();

const FileContextProvider = (props) => {
  const { children } = props
  const [ error, setError ] = useState(false)
  const [ loading, setLoading ] = useState(false)
  const [ progress, setProgress ] = useState(null)
  const [ currentPath, setCurrentPath ] = useState('')
  const [ files, setFiles ] = useState([])
  const [ directories, setDirectories ] = useState([])
  const [ totalSpace, setTotalSpace ] = useState(0)
  const [ usedSpace, setUsedSpace ] = useState(0)
  const [ selectedItem, setSelectedItem ] = useState(null)
  const selectTimestamp = useRef(0)
  const { openJob } = useJob();

  const fetch = useCallback(async () => {
    try {
      setLoading(true)
      const response = await ApiClient.fsGetPath(currentPath);
      setLoading(false)

      if(response.type === "directory") {
        updateList(response.data);
      }

      return response.data.files
      // TODO: throw on file??
    } catch(e){
      setLoading(false)
      setError(true);
    }
  }, [currentPath])

  const updateList = useCallback(data => {
    const directories = data.files.filter(f => f.type === 'd');
    const files = data.files.filter(f => f.type === 'f');
    const totalSpace = data.total_space;
    const usedSpace = totalSpace - data.free_space;

    setDirectories(directories)
    setFiles(files)
    setTotalSpace(totalSpace)
    setUsedSpace(usedSpace)
  }, [])

  const openSelectedItem = useCallback(async () => {
    if(!selectedItem)
      return
    
    if(selectedItem.type === 'd'){
      let nextPath;

      if(selectedItem.name === ".."){
        let parts = currentPath.split('/');
        nextPath = parts.slice(0, parts.length - 1).join('/');
      } else {
        nextPath = currentPath + '/' + selectedItem.name.toLowerCase();
      }

      setCurrentPath(nextPath)
      setSelectedItem(null)
      selectTimestamp.current = 0

      fetch();
    } else {
      const path = currentPath + '/' + selectedItem.name.toLowerCase();
      openJob(path);
    }
  }, [selectedItem, currentPath])

  const setSelected = useCallback(item => {
    const timestamp = Date.now();

    if(item === selectedItem){
      // Test for double click
      if(timestamp - selectTimestamp.current < 500) {
        openSelectedItem();
      } else {
        selectTimestamp.current = timestamp
      }
    } else {
      setSelectedItem(item)
    }
  }, [selectedItem])


  const unsetSelected = useCallback(() => {
    setSelectedItem(null)
    selectTimestamp.current = 0
  }, [])

  const handleUpload = useCallback(async files => {
    await ApiClient.fsUpload(
      currentPath,
      files[0],
      progress => setProgress(progress)
    );

    setProgress(null)
    const newfiles = await fetch()
    const newItem = newfiles.find(file => file.name === files[0].name)
    setSelectedItem(newItem);
  }, [currentPath])

  const deleteSelectedItem = useCallback(async () => {
    try {
      await ApiClient.fsDelete(currentPath + '/' + selectedItem.name.toLowerCase());
      selectedItem(null)
      await fetch()
    } catch(e){
      alert("Delete failed!");
    }
  }, [currentPath, selectedItem])

  useEffect(fetch, [])

  return (
      <FileContext.Provider
          value={{
            error,
            loading,
            progress,

            currentPath,
            files,
            directories,
            totalSpace,
            usedSpace,
            selectedItem,

            setSelected,
            unsetSelected,
            handleUpload,
            openSelectedItem,
            deleteSelectedItem
          }}
      >
        { children }
      </FileContext.Provider>
  )
}

export { FileContext, FileContextProvider }
