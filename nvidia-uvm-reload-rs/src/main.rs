use dbus::blocking::Connection;
use dbus_crossroads::Crossroads;
use duct::cmd;

fn main() -> Result<(), dbus::Error> {
    let c = Connection::new_system()?;
    c.request_name("org.powertools", false, true, false)?;
    let mut cr = Crossroads::new();

    let token = cr.register("org.powertools", |b| {
        b.method("RestartNvidia", (), (), move |_, _, (): ()| {
            println!("Restarting nvidia_uvm");
            let _ = cmd!("rmmod", "nvidia_uvm").run();
            let _ = cmd!("modprobe", "nvidia_uvm").run();
            println!("Finished restarting nvidia_uvm");
            Ok(())
        });
    });

    cr.insert("/", &[token], ());
    cr.serve(&c)?;

    Ok(())
}
