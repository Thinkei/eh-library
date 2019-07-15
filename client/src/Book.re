type book = {
  title: string,
};

[@react.component]
let make = () => {
  <div>{ReasonReact.string("Book re")}</div>
};
