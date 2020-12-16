import axios from 'axios';
const BASE_PATH = `http://${process.env.REACT_APP_DEVICE_IP}`;

class ApiFileDownload {
  constructor(response){
    this.response = response;
  }

  async download(progressCallback){
    const contentLength = this.response.headers.get('content-length');
    const reader = this.response.body.getReader();

    let receivedLength = 0;
    let chunks = [];
    while(true) {
      const {done, value} = await reader.read();

      if (done) {
        break;
      }

      chunks.push(value);
      receivedLength += value.length;

      const progress = 100 * receivedLength / contentLength;
      progressCallback(progress);
    }

    const chunksAll = new Uint8Array(receivedLength);
    let position = 0;
    for(let chunk of chunks) {
      chunksAll.set(chunk, position);
      position += chunk.length;
    }

    return new TextDecoder("utf-8").decode(chunksAll);
  }

}

function fileToArrayBuffer(file){
  return new Promise(res => {
    const reader = new FileReader();

    reader.onload = () => {
      res(reader.result);
    }

    reader.readAsArrayBuffer(file);
  });
}

export default class ApiClient {
  static async fsGetPath(path){
    if(path.startsWith('/'))
      path = path.slice(1);

    const response = await fetch(BASE_PATH + '/fs/' + path);
    const contentType = response.headers.get('Content-Type');

    switch(contentType){
      case "application/json":
        return {
          type: 'directory',
          data: await response.json()
        };
      case "text/plain":
        return {
          type: 'file',
          data: new ApiFileDownload(response)
        };
    }
  }

  static async fsUpload(path, file, progressCallback){
    const dataBuffer = await fileToArrayBuffer(file);
    const url = BASE_PATH + '/fs/' + path + '/' + file.name;
    const config = {
      onUploadProgress: progressEvent => {
        const percentCompleted = Math.round( (progressEvent.loaded * 100) / progressEvent.total );
        progressCallback(percentCompleted);
      }
    };

    await axios.post(url, dataBuffer, config);
  }

  static async fsDelete(path){
    if(path.startsWith('/'))
      path = path.slice(1);

    const req = await fetch(BASE_PATH + '/fs/' + path, { method: 'DELETE' });
    const contentType = req.headers.get('Content-Type');

    const result = await req.json();

    if(!result.success)
      throw new Error('Cannot delete, are you trying to delete a folder with stuff in it?');
  }

  static async getJob(){
    const req = await fetch(BASE_PATH + '/job', { method: 'GET' });
    return await req.json()
  }

  static async creatJob(filename){
    const payload = { filename }
    const req = await fetch(
      BASE_PATH + '/job',
      {
        method: 'POST',
        body: JSON.stringify(payload)
      }
    );
    const body = await req.json()

    if(body.error)
      throw new Error(body.error)

    return body
  }
}
