// This bring all Belt's module into scope.
open Belt;

// A React component, so simple!
module App = {
  [@react.component]
  let make = () => {
    <section className="todoapp">
      <header className="header">
        <h1> {ReasonReact.string("RR TODOs")} </h1>
      </header>
      <section className="main" />
    </section>;
  };
};

// Finally render it.
ReactDOMRe.renderToElementWithId(<App />, "root");
