export function bytesToString(bytes){
  const suffixes = ['B', 'kB', 'MB', 'GB', 'TB'];
  let count = 0, size = bytes;

  while(size >= 1024){
    size /= 1024;
    count++;
  }
  return `${size.toFixed(2)} ${suffixes[count]}`;
}
