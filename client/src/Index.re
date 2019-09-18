[%bs.raw {|require("@ehrocks/eh-ant-design/styles/eh-ant-design.css")|}];

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
    <App />
  </ReasonApollo.Provider>,
  "root",
);
