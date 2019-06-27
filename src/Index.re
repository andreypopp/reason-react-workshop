// This bring all Belt's module into scope.
open Belt;

// A React component, so simple!
module App = {
  [@react.component]
  let make = () => {
    <section className="todoapp">
      <header className="header">
        <h1> {ReasonReact.string("RR TODOs")} </h1>
        <input
          className="new-todo"
          placeholder="What needs to be done?"
          autoFocus=true
        />
      </header>
      <section className="main">
        <input
          className="toggle-all"
          id="toggle-all"
          type_="checkbox"
          checked=false
        />
        <label htmlFor="toggle-all">
          {ReasonReact.string("Mark all as complete")}
        </label>
        <ul className="todo-list">
          <li>
            <div className="view">
              <input className="toggle" type_="checkbox" checked=false />
              <label> {ReasonReact.string("Learn Reason")} </label>
              <button className="destroy" />
            </div>
          </li>
        </ul>
      </section>
      <footer className="footer">
        <span className="todo-count">
          <strong> {ReasonReact.string("0 items left")} </strong>
        </span>
        <ul className="filters">
          <li>
            <a className="selected" href="#/">
              {ReasonReact.string("All")}
            </a>
          </li>
          <li> <a href="#/active"> {ReasonReact.string("Active")} </a> </li>
          <li>
            <a href="#/completed"> {ReasonReact.string("Completed")} </a>
          </li>
        </ul>
        <button className="clear-completed">
          {ReasonReact.string("Clear completed")}
        </button>
      </footer>
    </section>;
  };
};

// Finally render it.
ReactDOMRe.renderToElementWithId(<App />, "root");