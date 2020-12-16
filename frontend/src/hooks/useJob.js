import { useCallback, useContext } from 'react'
import { JobContext } from "../context/JobContext"
import ApiClient from '../models/ApiClient'


export const useJob = () => {
    const { setJob } = useContext(JobContext)
    
    const openJob = useCallback(async (path) => {
        try {
            const response = await ApiClient.creatJob(path);
            setJob(response)
        } catch(e){
            // Show error modal
        }
    }, [])

    return { openJob }
}