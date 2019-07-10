type book = {
  title: string,
  tags: list(string)
};

[@react.component]
let make = () => <div>{ReasonReact.string("New book")}</div>
