import { useEffect } from 'react'

export const useAsyncEffect = (handler, vars) => {
    useEffect(() => {
        handler()
    }, vars)
}