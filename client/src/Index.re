module App = {
  [@react.component]
  let make = () => <h1>{ReasonReact.string("Hello: This is EH Library!")}</h1>;
};

ReactDOMRe.renderToElementWithId(<App />, "root");
