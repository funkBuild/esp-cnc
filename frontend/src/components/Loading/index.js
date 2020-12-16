import React from 'react'
import loadingImage from './loading.svg';

import './Loading.css'

export const LoadingProgress = (props) => {
    const { progress, hidden } = props;

    if(hidden)
        return null

    return (
        <div className="progressContainer">
            <div className="progressBar">
                <span style={{width: `${progress}%`}}>
                &nbsp;
                </span>
            </div>
            <span>{ progress.toFixed(0) }%</span>
        </div>
    )
}

export const Loading = (props) => {
    const { hidden } = props;

    if(hidden)
        return null
        
    return (
        <div className="loading">
        <img src={ loadingImage } alt="Loading"/>
        </div>
    )
}