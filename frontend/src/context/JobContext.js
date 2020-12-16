import React, { useState } from 'react';
import ApiClient from '../models/ApiClient'
import { useAsyncEffect } from '../util/useAsyncEffect'
import GcodeFile from '../models/gcode';
import State from '../models/state';

export const JobContext = React.createContext();

export const JobContextProvider = (props) => {
    const { children } = props
    const [ job, setJob ] = useState(null)
    const [ progress, setProgress ] = useState(null)
    const [ loadedFile, setLoadedFile ] = useState(null)

    useAsyncEffect(async () => {
        const jobResponse = await ApiClient.getJob()

        if(jobResponse.state == "empty"){
            setJob(null)
        } else {
            setJob(jobResponse)
        }
    }, [])

    useAsyncEffect(async () => {
        if(!job)
            return;

        console.dir(job)
        
        const resp = await ApiClient.fsGetPath(job.filename);
  
        const data = await resp.data.download(progress => {
            setProgress(progress);
        });
  
        setProgress(null);

        const gcodeFile = new GcodeFile(data);
  
        State.setModel(gcodeFile);

        setLoadedFile({
            gcodeLines: gcodeFile.toGcodeLines(),
            name: job.filename,
            path: job.filename
        })
    }, [job])

    return (
        <JobContext.Provider
            value={{
                job,
                setJob,
                progress,
                loadedFile
            }}
        >
            { children }
        </JobContext.Provider>
    )
}