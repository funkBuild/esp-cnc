import React, { Component } from 'react';

export const ThemeContext = React.createContext();
export const ThemeContextConsumer = ThemeContext.Consumer;

export class ThemeContextProvider extends Component {
  state = {
    theme: "light",
  };

  setTheme(theme){
    this.setState({theme});
  }

  render() {
    const { children } = this.props;

    return (
      <ThemeContext.Provider
        value={{
          ...this.state,
          setThem
        }}
      >
        {children}
      </ThemeContext.Provider>
    );
  }
}

