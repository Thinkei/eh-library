type book = { title: string, };

[@react.component]
let make = (~title) => {
  <div>
    <span>{ReasonReact.string(title)}</span>
  </div>
};
