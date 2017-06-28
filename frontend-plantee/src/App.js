import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import Tinderable from "react-tinderable";

const data = [{title: 'lala', text: 'dingding', id: '1', image: 'logo.svg'}];

class App extends Component {
  render() {
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>Welcome to my webpage!</h2>
        </div>
        <p className="App-intro">
          To get started, edit <code>src/App.js</code> and save to reload.
        </p>
        <Tinderable intialCardsData={data} />
      </div>
    );
  }
}

export default App;
