[@react.component]
let make = (~firstName, ~lastName) => {
  let ln =
    switch (lastName) {
    | Some(str) => str
    | None => "N/A"
    };
  <div>
    <Ehd.Typography.Title>
      {ReasonReact.string("Full name:")}
    </Ehd.Typography.Title>
    <Ehd.Typography.Text>
      {ReasonReact.string(firstName ++ " " ++ ln)}
    </Ehd.Typography.Text>
  </div>;
};
