let rec times = (x, fn) => {
  switch (x) {
  | 1 => [fn()]
  | _ => [fn(), ...times(x - 1, fn)]
  };
};

Random.init(int_of_float(Js.Date.now()));
let r = () => 256 |> Random.int |> string_of_int;

let randomColor = () => {
  "rgb(" ++ r() ++ "," ++ r() ++ "," ++ r() ++ ")";
};

[@react.component]
let make = (~title, ~imageUrl, ~tags) =>
  <Ehd.Col offset=1 span=6>
    <Ehd.Card cover={<img src=imageUrl />}>
      <Ehd.Typography.Text> {ReasonReact.string(title)} </Ehd.Typography.Text>
      <Ehd.Typography.Paragraph>
        {switch (tags) {
         | None => ReasonReact.null
         | Some(str) =>
           str
           |> Js.String.split(",")
           |> Array.map(tag =>
                <Ehd.Tag color={randomColor()}>
                  {ReasonReact.string(tag)}
                </Ehd.Tag>
              )
           |> ReasonReact.array
         }}
      </Ehd.Typography.Paragraph>
    </Ehd.Card>
  </Ehd.Col>;
