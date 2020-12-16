import React, { useContext } from 'react';
import ThreeDisplay from './components/ThreeDisplay';
import FileManager from './components/FileManager';
import PositionWidget from './components/PositionWidget';
import JogControls from './components/JogControls';
import { FileContextProvider } from './components/FileManager/FileContext';
import { JobView } from "./components/JobView"
import { JobContextProvider, JobContext } from "./context/JobContext"
import './App.css';

const App = () => {
  const { job } = useContext(JobContext)

  return (
    <div className="App">
      <ThreeDisplay />

      <div className="leftMenu">
        { job ? <JobView /> : <FileManager /> }
      </div>

      <div className="rightMenu">
        <PositionWidget />
        <JogControls />
      </div>
    </div>
  )
}

export default () => {
    return (
      <JobContextProvider>
        <FileContextProvider>
          <App />
        </FileContextProvider>
      </JobContextProvider>
    );
}
