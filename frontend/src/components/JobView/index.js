import React, { useContext } from 'react'
import { JobContext } from "../../context/JobContext"
import Window from '../Window';
import GcodeViewer from '../GcodeViewer'
import { LoadingProgress } from "../Loading"

export const JobView = () => {
    const { progress } = useContext(JobContext)

    return (
        <Window>
            <LoadingProgress hidden={progress == null} progress={progress} />
            <GcodeViewer />
        </Window>
    )
}